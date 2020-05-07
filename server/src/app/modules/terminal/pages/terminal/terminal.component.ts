import { Component, OnInit } from '@angular/core';
import { TerminalWindowService, IMessage } from '../../services/terminal-window.service';

@Component({
  selector: 'app-terminal',
  templateUrl: './terminal.component.html',
  styleUrls: ['./terminal.component.scss']
})

export class TerminalComponent implements OnInit {
  public commands: IMessage[] = [];

  constructor(private terminalWindow: TerminalWindowService) { }

  ngOnInit(): void {
    this.terminalWindow.on((cmnd: IMessage) => {
      this.commands.push(cmnd);
    });

  }

}
