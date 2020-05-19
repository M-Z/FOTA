import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

import { UploadRoutingModule } from './upload-routing.module'
import { UploadComponent } from './pages/upload/upload.component';
import { SimpleNotificationsModule, Options, NotificationAnimationType } from 'angular2-notifications';
import { ReactiveFormsModule } from '@angular/forms';
import { SharedModule } from 'app/shared/shared.module';

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
    UploadComponent
  ],
  imports: [
    CommonModule,
    UploadRoutingModule,
    SharedModule,
    ReactiveFormsModule,
    SimpleNotificationsModule.forRoot(notificationOptions)
  ]
})
export class UploadModule { }
