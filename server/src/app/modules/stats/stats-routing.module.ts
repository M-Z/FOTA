import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { StatsComponent } from './pages/stats/stats.component';

const routes: Routes = [{
  path: '',
  component: StatsComponent
}];

@NgModule({
  imports: [
    RouterModule.forChild(routes)
  ],
  exports: [
    RouterModule
  ]
})

export class StatsRoutingModule { }
