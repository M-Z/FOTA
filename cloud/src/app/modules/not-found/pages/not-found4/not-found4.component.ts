import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-not-found4',
  templateUrl: './not-found4.component.html',
  styleUrls: ['./not-found4.component.scss']
})
export class NotFound4Component {
  @Input() suggestedPath: string;

  constructor() { }
}
