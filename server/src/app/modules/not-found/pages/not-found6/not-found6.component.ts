import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-not-found6',
  templateUrl: './not-found6.component.html',
  styleUrls: ['./not-found6.component.scss']
})
export class NotFound6Component {
  @Input() suggestedPath: string;

  constructor() { }

}
