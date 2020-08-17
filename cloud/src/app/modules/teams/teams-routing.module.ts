import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { TeamsComponent } from './pages/teams/teams.component';
import { TeamComponent } from './pages/team/team.component';

const routes: Routes = [{
  path: '',
  component: TeamsComponent
}, {
  path: ':teamID',
  component: TeamComponent
}];

@NgModule({
  imports: [
    RouterModule.forChild(routes)
  ],
  exports: [
    RouterModule
  ]
})

export class TeamsRoutingModule { }
