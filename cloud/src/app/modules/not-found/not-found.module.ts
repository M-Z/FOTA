import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { NotFoundRoutingModule } from './not-found-routing.module';
import { NotFoundDirective } from './directives/not-found.directive';
import { NotFoundComponent } from './pages/not-found/not-found.component';
import { NotFound1Component } from './pages/not-found1/not-found1.component';
import { NotFound2Component } from './pages/not-found2/not-found2.component';
import { NotFound3Component } from './pages/not-found3/not-found3.component';
import { NotFound4Component } from './pages/not-found4/not-found4.component';
import { NotFound5Component } from './pages/not-found5/not-found5.component';
import { NotFound6Component } from './pages/not-found6/not-found6.component';
import { NotFound7Component } from './pages/not-found7/not-found7.component';

@NgModule({
  declarations: [
    NotFoundDirective,
    NotFoundComponent,
    NotFound1Component,
    NotFound2Component,
    NotFound3Component,
    NotFound4Component,
    NotFound5Component,
    NotFound6Component,
    NotFound7Component
  ],
  imports: [
    CommonModule,
    NotFoundRoutingModule
  ],
  entryComponents: [  // you can tell the OTC to also compile this components so they are available at runtime.
    NotFound1Component,
    NotFound2Component,
    NotFound3Component,
    NotFound4Component,
    NotFound5Component,
    NotFound6Component,
    NotFound7Component
  ]
})
export class NotFoundModule { }
