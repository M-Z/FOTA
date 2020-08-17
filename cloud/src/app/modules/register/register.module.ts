import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { SharedModule } from 'app/shared/shared.module';
import { RegisterRoutingModule } from './register-routing.module';
import { RegisterComponent } from './pages/register.component';
import { SimpleNotificationsModule, NotificationAnimationType, Options } from 'angular2-notifications';
import { ReactiveFormsModule } from '@angular/forms';
import { AnQrcodeModule } from 'an-qrcode';
import { PasswordStrengthMeterModule } from 'angular-password-strength-meter';

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
    RegisterComponent
  ],
  imports: [
    CommonModule,
    SharedModule,
    ReactiveFormsModule,
    RegisterRoutingModule,
    AnQrcodeModule,
    PasswordStrengthMeterModule,
    SimpleNotificationsModule.forRoot(notificationOptions)
  ]
})
export class RegisterModule { }
