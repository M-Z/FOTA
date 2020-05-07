import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-footer',
  templateUrl: './footer.component.html',
  styleUrls: ['./footer.component.scss']
})
export class FooterComponent implements OnInit {

  public today: number;

  constructor() {}

  ngOnInit(): void {
    this.today = Date.now();
  }

}
