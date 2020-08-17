import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { LoginRoutingModule } from './login-routing.module';
import { LoginComponent } from './pages/login/login.component';
import { ReactiveFormsModule } from '@angular/forms';
import { SharedModule } from 'app/shared/shared.module';
import { NotificationAnimationType, Options, SimpleNotificationsModule } from 'angular2-notifications';

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
    LoginComponent
  ],
  imports: [
    CommonModule,
    SharedModule,
    ReactiveFormsModule,
    LoginRoutingModule,
    SimpleNotificationsModule.forRoot(notificationOptions)
  ]
})
export class LoginModule { }
