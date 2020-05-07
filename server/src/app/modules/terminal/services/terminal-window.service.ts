import { Injectable } from '@angular/core';
import { WebsocketService } from 'app/core/services/WebSocket/websocket.service';

export interface IMessage {
  string: string;
  output?: string;
}

@Injectable({
  providedIn: 'root'
})
export class TerminalWindowService {

  constructor(private wsService: WebsocketService) {}

  on(callback: (_: any) => void) {
    this.wsService.on<IMessage>('command').subscribe((messages: IMessage) => {
      callback(messages);
    });
  }

  send(commands: string) {
    this.wsService.send('command', commands);
  }
}
