import { Component, OnInit, ViewChild, ComponentFactoryResolver } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { take } from 'rxjs/operators';

import { NotFoundDirective } from '../../directives/not-found.directive';
import { NotFound1Component } from '../not-found1/not-found1.component';
import { NotFound2Component } from '../not-found2/not-found2.component';
import { NotFound3Component } from '../not-found3/not-found3.component';
import { NotFound4Component } from '../not-found4/not-found4.component';
import { NotFound5Component } from '../not-found5/not-found5.component';
import { NotFound6Component } from '../not-found6/not-found6.component';
import { NotFound7Component } from '../not-found7/not-found7.component';


@Component({
  selector: 'app-not-found',
  template: `<ng-template appNotFound></ng-template>`
})
export class NotFoundComponent implements OnInit {
  suggestedPath: string;

  @ViewChild(NotFoundDirective, { static: true }) pageHost: NotFoundDirective;

  constructor(private route: ActivatedRoute, private r: ComponentFactoryResolver) { }

  ngOnInit() {

    // Used after the service detected the guessed 'route'
    this.route.data.pipe(take(1))
      .subscribe((data: { path: string }) => {
        this.suggestedPath = data.path;
      });

    this.loadComponent();
  }

  // Load random component from array
  loadComponent() {
    const notFoundPages = [NotFound1Component, NotFound2Component, NotFound3Component,
      NotFound4Component, NotFound5Component, NotFound6Component, NotFound7Component];

    const notFoundPage = notFoundPages[Math.floor(Math.random() * notFoundPages.length)];

    const componentFactory = this.r.resolveComponentFactory(notFoundPage);

    const viewContainerRef = this.pageHost.viewContainerRef;

    viewContainerRef.clear();
    const componentRef = viewContainerRef.createComponent(componentFactory);
    (componentRef.instance).suggestedPath = this.suggestedPath;
  }


}
