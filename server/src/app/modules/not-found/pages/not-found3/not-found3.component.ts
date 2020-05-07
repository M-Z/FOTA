import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-not-found3',
  templateUrl: './not-found3.component.html',
  styleUrls: ['./not-found3.component.scss']
})
export class NotFound3Component {
  @Input() suggestedPath: string;

  constructor() { }

}
