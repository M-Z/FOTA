import { Component } from '@angular/core';
import { FormGroup, FormBuilder, Validators } from '@angular/forms';
import { NotificationsService } from 'angular2-notifications';
import { AuthService } from 'app/core/services/Authentication/authentication.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent {

  loginForm: FormGroup;

  constructor(
    public fb: FormBuilder,
    private notify: NotificationsService,
    private authService: AuthService
  ) {

    this.loginForm = this.fb.group({
      username: ['', [
        Validators.required,
        Validators.minLength(10),
        Validators.maxLength(64)
      ]],
      password: ['', [
        Validators.required,
        Validators.minLength(12),
        Validators.maxLength(128)
      ]]
    })
  }

  loginUser() {
    this.authService.login(this.loginForm.value).subscribe({
      next: (response: {error: string}) => {
        if (response.error) {
          this.notify.error(response.error || "Some error occured while logging you in.");
        }
      },
      error: (error: { error: string; }) => {
        this.notify.error(error.error || "Some error occured while logging you in.");
      }
    });
  }
}
