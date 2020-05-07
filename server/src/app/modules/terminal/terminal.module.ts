import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { TerminalComponent } from './pages/terminal/terminal.component';
import { TerminalRoutingModule } from './terminal-routing.module';

@NgModule({
  declarations: [
    TerminalComponent
  ],
  imports: [
    CommonModule,
    TerminalRoutingModule,
  ]
})
export class TerminalModule { }
