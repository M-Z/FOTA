import { Component, EventEmitter, Output, Input } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { HttpService } from 'app/core/services/HTTP/http.service';
import { ActivatedRoute } from '@angular/router';
import { User } from 'app/core/services/Authentication/authentication.service';

@Component({
  selector: 'app-new-user-form',
  templateUrl: './new-user-form.component.html',
  styleUrls: ['./new-user-form.component.scss']
})
export class NewUserFormComponent {
  private teamID: string;
  newUserForm: FormGroup;
  @Output() notifyUser: EventEmitter<any> = new EventEmitter();

  constructor(
    formBuilder: FormBuilder,
    private http: HttpService,
    activatedRoute: ActivatedRoute
  ) {
    activatedRoute.params.subscribe((params: { [x: string]: string; }) => {
      this.teamID = params['teamID'];
    });

    this.newUserForm = formBuilder.group({
      email: ['', [
        Validators.required,
        Validators.email
      ]],
      role: ['', [
        Validators.required
      ]]
    })
  }

  onSubmit() {
    const formValues = this.newUserForm.value;

    this.http.invoke({
      method: 'POST',
      path: 'user/add',
      body: {
        email: formValues.email,
        role: formValues.role,
        teamID: this.teamID
      }
    }).subscribe({
      next: (res: { data: string, member?: User }) => {

        if (res.data == 'success') {
          this.notifyUser.emit({
            type: 'success',
            message: 'Invitation sent!',
            member: res.member
          });
        } else {
          this.notifyUser.emit({
            type: 'error',
            message: res.data
          });
        }
      },
      error: () =>
        this.notifyUser.emit({
          type: 'error',
          message: "Couldn't add the new user."
        })
    })
  }

}
