import { Component, Input } from '@angular/core';

@Component({
  selector: 'app-not-found5',
  templateUrl: './not-found5.component.html',
  styleUrls: ['./not-found5.component.scss']
})
export class NotFound5Component {
  @Input() suggestedPath: string;

  constructor() { }

}
