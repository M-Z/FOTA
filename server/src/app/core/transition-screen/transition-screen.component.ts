import { Component } from '@angular/core';
import * as NProgress from 'nprogress';

import {
  Router,
  Event as RouterEvent,
  NavigationStart,
  NavigationEnd,
  NavigationCancel,
  NavigationError
} from '@angular/router';

@Component({
  selector: 'app-transition-screen',
  templateUrl: './transition-screen.component.html',
  styleUrls: ['./transition-screen.component.scss']
})
export class TransitionScreenComponent {
  public showOverlay: boolean;

  constructor(private router: Router) {
    this.showOverlay = false;

    router.events.subscribe((event: RouterEvent) => this.navigationInterceptor(event));
  }

  // Shows and hides the loading spinner during RouterEvent changes
  navigationInterceptor(event: RouterEvent): void {

    if (event instanceof NavigationStart) {
      NProgress.start();
      this.showOverlay = true;
    }

    if (event instanceof NavigationEnd || event instanceof NavigationCancel || event instanceof NavigationError) {
      NProgress.done();
      this.showOverlay = false;
    }

  }

}
