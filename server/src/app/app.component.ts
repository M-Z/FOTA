import { Component } from '@angular/core';
import { ActivatedRoute, Router, NavigationEnd, RouterOutlet } from '@angular/router';
import { Title } from '@angular/platform-browser';
import { filter, map } from 'rxjs/operators';
import { routeAnimations } from './shared/animations/animations';
import { ScriptStoreService } from './shared/services/scriptStore.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  animations: [
    routeAnimations
  ]
})

export class AppComponent {

  constructor(
    private router: Router,
    private activatedRoute: ActivatedRoute,
    private titleService: Title,
    importScripts: ScriptStoreService
  ) {

    importScripts.load('bootstrap', 'styles');

    // Change title from router
    this.router.events.pipe(
      filter(event => event instanceof NavigationEnd),
      map(() => {
        let child = this.activatedRoute.firstChild;

        // Go down the tree
        while (child) {

          if (child.firstChild) {
            child = child.firstChild;
          } else if (child.snapshot.data && child.snapshot.data.title) {
            return child.snapshot.data.title;
          } else {
            return null;
          }
        }

        return null;
      })
    ).subscribe((data: any) => {
      if (data) {
        this.titleService.setTitle(data + ' - FOTA');
      }
    });
  }

  // Return current router info for animations
  prepareRoute(outlet: RouterOutlet) {
    return outlet && outlet.activatedRouteData && outlet.activatedRouteData.animation;
  }

}
