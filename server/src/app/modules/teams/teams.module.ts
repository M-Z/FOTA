import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ReactiveFormsModule } from '@angular/forms';

import { NotificationAnimationType, Options, SimpleNotificationsModule } from 'angular2-notifications';
import { SharedModule } from 'app/shared/shared.module';
import { TeamsRoutingModule } from './teams-routing.module';

import { AddModalComponent } from './components/add-modal/add-modal.component';
import { NewUserFormComponent } from './components/new-user-form/new-user-form.component';
import { NewTeamFormComponent } from './components/new-team-form/new-team-form.component';
import { TeamsComponent } from './pages/teams/teams.component';
import { TeamComponent } from './pages/team/team.component';

const notificationOptions: Options = {
  position: ['bottom', 'left'],
  timeOut: 5000,
  showProgressBar: true,
  pauseOnHover: true,
  clickToClose: true,
  animate: NotificationAnimationType.FromLeft
};

@NgModule({
  declarations: [
    AddModalComponent,
    NewUserFormComponent,
    NewTeamFormComponent,
    TeamsComponent,
    TeamComponent
  ],
  imports: [
    CommonModule,
    ReactiveFormsModule,
    SharedModule,
    TeamsRoutingModule,
    SimpleNotificationsModule.forRoot(notificationOptions)
  ]
})
export class TeamsModule { }
