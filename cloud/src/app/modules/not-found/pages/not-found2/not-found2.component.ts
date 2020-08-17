import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-not-found2',
  templateUrl: './not-found2.component.html',
  styleUrls: ['./not-found2.component.scss']
})
export class NotFound2Component {
  @Input() suggestedPath: string;

  constructor() { }

}
