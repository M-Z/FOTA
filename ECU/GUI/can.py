import mcp2515
import spidev
import RPi.GPIO as GPIO

RX_msg = []
spi = spidev.SpiDev()


def reset():
    reset_instruction = [0xC0]
    spi.writebytes(reset_instruction)


def readReg(addr):
    buf_rd = [0x03, addr, 0x55]
    buf_rd = spi.xfer2(buf_rd)
    return int(buf_rd[2])


def writeReg(addr, val):
    buf_wrt = [0x02, addr, val]
    spi.writebytes(buf_wrt)


def ReadRxBuffer(start_reg, length):
    inst = 0x90 | (start_reg << 1)
    buf = [inst]
    for i in range(length):
        buf.append(0x55)
    buf = spi.xfer2(buf)
    print("buffer in request =", buf)
    return buf


def LoadTxBuffer(start_reg, data):
    inst = 0x40 | start_reg
    buf = [inst]
    buf.extend(data)
    spi.writebytes(buf)


def RequestToSend(transmit_buffer):
    inst = [(0x80 | (1 << transmit_buffer))]
    spi.writebytes(inst)


def BitModify(addr, mask, value):
    buf = [0x05, addr, mask, value]
    spi.writebytes(buf)


def ReadStatus():
    buf = [0xA0, 0x55]
    buf = spi.xfer2(buf)
    return int(buf[1])


def RxStatus():
    buf = [0xB0, 0x55]
    buf = spi.xfer2(buf)
    return int(buf[1])


def SetFilters(filters):
    writeReg(mcp2515.RXM0SIDH, 0xFF)
    writeReg(mcp2515.RXM0SIDL, 0xE0)
    writeReg(mcp2515.RXM1SIDH, 0xFF)
    writeReg(mcp2515.RXM1SIDL, 0xE0)
    writingregister = mcp2515.RXF0SIDH
    for i in range(len(filters)):
        low = filters[i] & 0x007
        high = (filters[i] & 0x7F8) >> 3
        writeReg(writingregister, high)
        writeReg(writingregister + 1, low << 5)
        writingregister = writingregister + 4


def init(filters):
    spi.open(0, 0)
    spi.max_speed_hz = 10000
    # Reset all interrupts
    writeReg(mcp2515.CANINTF, 0x00)
    # Start Configuration Mode
    writeReg(mcp2515.CANCTRL, 0x80)
    #    print(hex(readReg(mcp2515.CANSTAT)))
    # setting PS1, PS2,brp
    writeReg(mcp2515.CNF1, 0x00)
    writeReg(mcp2515.CNF2, 0x09)
    writeReg(mcp2515.CNF3, 0x02)
    # set filters
    SetFilters(filters)

    # request normal mode
    writeReg(mcp2515.CANCTRL, 0x00)

    # alow autoretransmission
    BitModify(mcp2515.CANCTRL, 0x08, 0x00)

    # turn on receive interrupts
    writeReg(mcp2515.CANINTE, 0x03)

    # Allow rollover to RXB1 if RXB0 is full and set filter selection
    writeReg(mcp2515.RXB0CTRL, 0x04)
    print("Initialization Done")


# TX_msg=[ID,format,type,length,data]


def transmit_buffer0(TX_msg):
    print("Sending Message")
    tx_flag = readReg(mcp2515.TXB0CTRL)
    tx_flag = (tx_flag >> 3) & 0x01
    if not tx_flag:
        # setting the standard identifier
        low = TX_msg["ID"] & (0x007)
        low = low << 5
        # writeReg(TXB0SIDL,low)
        high = TX_msg["ID"] & (0x7F8)
        high = high >> 3
        # writeReg(TXB0SIDH,high)
        data = [high, low, 0x55, 0x55]
        # setting the length of the data and the type
        len = TX_msg["length"]
        if TX_msg["type"] == "data_frame":
            len = len & (0x0F)
            # writeReg(TXB0DLC,len)
            data.append(len)
            # witing the data
            data.extend(TX_msg["data"])
            # writeReg(TXB0D+i,TX_msg[4][i])

        elif TX_msg["type"] == "remote_frame":
            len |= 0x40
            data.append(len)
            # writeReg(TXB0DLC,len)
        LoadTxBuffer(0, data)
        # Request to send
        RequestToSend(0)


def RX_interrupt(channel):
    print("In interrupt")
    flags = readReg(mcp2515.CANINTF)
    print(hex(readReg(mcp2515.CANINTF)))
    buffer = 0
    if (flags & 0x01) == 1:
        buf = ReadRxBuffer(0, 13)
        buffer = 0
        msg = {
            "ID": 0,
            "format": "standard_format",
            "type": "data_frame",
            "length": 0,
            "data": [0, 0, 0, 0, 0, 0, 0, 0],
        }
        msg["ID"] = (buf[1] << 3) | (buf[2] >> 5)
        msg["length"] = buf[5] & 0x0F
        for i in range(msg["length"]):
            msg["data"][i] = buf[6 + i]
        if msg["length"] == 0:
            msg["type"] = "remote_frame"
        RX_msg.append(msg)
        BitModify(mcp2515.CANINTF, 0x01, 0)
    if ((flags >> 1) & 0x01) == 1:
        buf = ReadRxBuffer(2, 13)
        buffer = 1
        msg = {
            "ID": 0,
            "format": "standard_format",
            "type": "data_frame",
            "length": 0,
            "data": [0, 0, 0, 0, 0, 0, 0, 0],
        }
        msg["ID"] = (buf[1] << 3) | (buf[2] >> 5)
        msg["length"] = buf[5] & 0x0F
        for i in range(msg["length"]):
            msg["data"][i] = buf[6 + i]
        if msg["length"] == 0:
            msg["type"] = "remote_frame"
        RX_msg.append(msg)
        BitModify(mcp2515.CANINTF, 0x02, 0)


#    print(hex(readReg(mcp2515.CANINTF)))
#    print('ERROR FLAGS = ',hex(readReg(mcp2515.EFLG)))
#    print(RX_msg)
