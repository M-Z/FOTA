import { Component } from '@angular/core';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.scss']
})

export class HomeComponent {

  public currentScene: string;
  public currentClock: string;

  constructor() {
    this.currentScene = 'animationStage1';
    this.currentClock = '07:00AM';
  }

}
