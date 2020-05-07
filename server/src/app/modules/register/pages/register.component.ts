import { Component, ElementRef, ViewChild } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Validators, FormBuilder, FormGroup } from '@angular/forms';
import { NotificationsService } from 'angular2-notifications';
import { AuthService, User, Team } from 'app/core/services/Authentication/authentication.service';
import { HttpService } from 'app/core/services/HTTP/http.service';
import { ValidationService } from 'app/shared/services/validation.service';
import { HttpEventType } from '@angular/common/http';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.scss']
})
export class RegisterComponent {
  token: string;
  newUserForm: FormGroup;
  valid: boolean;
  secret: string;
  registered: boolean;
  private userImage: File;
  user: User = new User;
  @ViewChild('fileLabel') fileLabel: ElementRef;

  constructor(
    activatedRoute: ActivatedRoute,
    formBuilder: FormBuilder,
    private http: HttpService,
    auth: AuthService,
    private notify: NotificationsService
  ) {
    this.valid = false;
    this.registered = false;

    activatedRoute.params.subscribe((params: { [x: string]: string; }) => {
      this.token = params['userKey'];
      const token = auth.parseToken(params['userKey']);

      if (!token.exp || auth.isExpired(token.exp) || !token.userId || !token.email || !token.team || !token.role) {
        return false;
      }

      this.user._id = token.userId;
      this.user.email = token.email;
      this.user.team = new Team;
      this.user.team.teamName = token.team;
      this.user.role = token.role;
      this.valid = true;

      this.newUserForm = formBuilder.group({
        email: [{
          value: this.user.email,
          disabled: true
        }],
        fullname: formBuilder.group({
          firstName: ['', [
            Validators.required,
            Validators.minLength(3),
            Validators.maxLength(12)
          ]],
          lastName: ['', [
            Validators.required,
            Validators.minLength(3),
            Validators.maxLength(12)
          ]]
        }),
        password: ['', [
          Validators.required,
          Validators.minLength(12),
          Validators.maxLength(100)
        ]],
        userImage: ['', [
          ValidationService.fileExtensions(['jpg', 'png', 'jpeg'])
        ]]
      });
    });

  }

  addFile(file: any) {
    if (file) {
      this.fileLabel.nativeElement.innerHTML = file.name;
      this.userImage = file;
    }
  }

  onSubmit() {
    const formValues = this.newUserForm.value;
    const formData = new FormData();
    formData.append('password', formValues.password);
    formData.append('email', this.user.email);
    formData.append('token', this.token);
    formData.append('firstName', formValues.fullname.firstName);
    formData.append('lastName', formValues.fullname.lastName);
    formData.append('userImage', this.userImage);

    this.http.invoke({
      method: 'POST',
      path: 'user/register',
      body: formData,
      requestHeader: {
        reportProgress: true,
        observe: 'events'
      }
    }).subscribe({
      next: (event) => {

        if (event.type === HttpEventType.DownloadProgress) {
          const progress = Math.round(event.loaded / event.total);
          switch (progress) {
            case 0.25:
              this.notify.success("25% uploaded.");
              break;
            case 0.5:
              this.notify.success("50% uploaded.");
              break;
            case 0.75:
              this.notify.success("75% uploaded.");
              break;
            case 1:
              this.notify.success("Image uploaded.");
              break;
          }
        }

        // 200
        if (event.type === HttpEventType.Response) {

          if (event.body.data == 'success') {
            // Show QR code
            this.registered = true;
            this.secret = "otpauth://totp/FOTA?secret=" + event.body.secret;
          } else {
            this.fileLabel.nativeElement.innerHTML = 'Choose Your Image';
            this.userImage = null;
            this.notify.error(event.body.data);
          }
        }
      },
      error: () => this.notify.error("Please try again later.")
    })
  }

}
