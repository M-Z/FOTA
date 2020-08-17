import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { StatsRoutingModule } from './stats-routing.module';
import { SharedModule } from 'app/shared/shared.module';
import { StatsComponent } from './pages/stats/stats.component';

@NgModule({
  declarations: [
    StatsComponent
  ],
  imports: [
    CommonModule,
    StatsRoutingModule,
    SharedModule
  ]
})
export class StatsModule { }
