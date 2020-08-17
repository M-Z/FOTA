import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-not-found1',
  templateUrl: './not-found1.component.html',
  styleUrls: ['./not-found1.component.scss']
})
export class NotFound1Component {
  @Input() suggestedPath: string;

  constructor() {}

}
