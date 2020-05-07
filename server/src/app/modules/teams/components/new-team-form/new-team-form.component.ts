import { Component, EventEmitter, Output, ViewChild, ElementRef } from '@angular/core';
import { FormGroup, Validators, FormBuilder } from '@angular/forms';
import { HttpService } from 'app/core/services/HTTP/http.service';
import { ValidationService } from 'app/shared/services/validation.service';
import { Team } from 'app/core/services/Authentication/authentication.service';
import { HttpEventType } from '@angular/common/http';

@Component({
  selector: 'app-new-team-form',
  templateUrl: './new-team-form.component.html',
  styleUrls: ['./new-team-form.component.scss']
})
export class NewTeamFormComponent {
  newTeamForm: FormGroup;
  private teamLogo: File;
  @ViewChild('fileLabel') fileLabel: ElementRef;
  @Output() notifyUser: EventEmitter<any> = new EventEmitter();

  constructor(
    formBuilder: FormBuilder,
    private http: HttpService
  ) {
    this.newTeamForm = formBuilder.group({
      teamName: ['', [
        Validators.required,
        Validators.minLength(4),
        Validators.maxLength(32)
      ]],
      teamDescription: ['', [
        Validators.minLength(12),
        Validators.maxLength(128)
      ]],
      teamLogo: ['', [
        ValidationService.fileExtensions(['jpg', 'png', 'jpeg']),
        Validators.required
      ]],
    })
  }

  addFile(file: any) {
    if (file) {
      this.fileLabel.nativeElement.innerHTML = file.name;
      this.teamLogo = file;
    }
  }

  onSubmit() {
    const formValues = this.newTeamForm.value;
    const formData = new FormData();
    formData.append('teamName', formValues.teamName);
    formData.append('teamDescription', formValues.teamDescription);
    formData.append('teamLogo', this.teamLogo);

    this.http.invoke({
      method: 'POST',
      path: 'team',
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
              this.notifyUser.emit({
                type: 'success',
                message: '25% uploaded.',
              });
              break;
            case 0.5:
              this.notifyUser.emit({
                type: 'success',
                message: '50% uploaded.',
              });
              break;
            case 0.75:
              this.notifyUser.emit({
                type: 'success',
                message: '75% uploaded.',
              });
              break;
            case 1:
              this.notifyUser.emit({
                type: 'success',
                message: 'Image uploaded.',
              });
              break;
          }
        }

        // 200
        if (event.type === HttpEventType.Response) {

          if (event.body.data == 'success') {
            this.notifyUser.emit({
              type: 'success',
              message: 'New team added!',
              member: event.body.member
            });
            this.newTeamForm.reset();
            this.fileLabel.nativeElement.innerHTML = 'Choose firmware';
            this.teamLogo = null;
          } else {
            this.notifyUser.emit({
              type: 'error',
              message: event.body.data
            });
          }
        }
      },
      error: () =>
        this.notifyUser.emit({
          type: 'error',
          message: "Couldn't add the new team"
        })
    })
  }

}
