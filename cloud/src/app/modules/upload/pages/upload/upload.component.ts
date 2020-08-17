import { Component, ViewChild, ElementRef } from '@angular/core';
import { NotificationsService } from 'angular2-notifications';
import { Validators, FormBuilder, FormGroup } from '@angular/forms';
import { ValidationService } from 'app/shared/services/validation.service';
import { formatDate } from '@angular/common';
import { HttpService } from 'app/core/services/HTTP/http.service';
import { Subject } from 'rxjs';
import { HttpEventType } from '@angular/common/http';

@Component({
  selector: 'app-upload',
  templateUrl: './upload.component.html',
  styleUrls: ['./upload.component.scss'],
})
export class UploadComponent {
  firmwareUploadForm: FormGroup;
  firmwareID: string;
  private hexFile: File;
  @ViewChild('major') major: ElementRef;
  @ViewChild('minor') minor: ElementRef;
  @ViewChild('patch') patch: ElementRef;
  @ViewChild('one') one: ElementRef;
  @ViewChild('two') two: ElementRef;
  @ViewChild('three') three: ElementRef;
  @ViewChild('four') four: ElementRef;
  @ViewChild('five') five: ElementRef;
  @ViewChild('six') six: ElementRef;
  @ViewChild('fileLabel') fileLabel: ElementRef;

  actionTaken: Subject<void> = new Subject<void>();

  private emitEventToChild() {
    this.actionTaken.next();
  }

  addFile(file: any) {
    if (file) {
      this.fileLabel.nativeElement.innerHTML = file.name;
      this.hexFile = file;
    }
  }

  constructor(
    private notify: NotificationsService,
    formBuilder: FormBuilder,
    private http: HttpService
  ) {
    // Array: is a variation of Group. The main difference is that its data gets
    // serialized as an array, as opposed to being serialized as an object in
    // case of FormGroup. This might be especially useful when you don’t know
    // how many controls will be present within the group, like in dynamic forms.
    this.firmwareUploadForm = formBuilder.group({
      name: ['', [
        Validators.required,
        Validators.minLength(4),
        Validators.maxLength(32)
      ]],
      firmwareID: [{ value: '', disabled: true }],
      newVersion: formBuilder.group({
        major: ['', [
          Validators.required,
          Validators.maxLength(2),
          Validators.min(0),
          Validators.max(99),
          Validators.pattern('^[0-9]+')
        ]],
        minor: ['', [
          Validators.required,
          Validators.maxLength(2),
          Validators.min(0),
          Validators.max(99),
          Validators.pattern('^[0-9]+')
        ]],
        patch: ['', [
          Validators.required,
          Validators.maxLength(2),
          Validators.min(0),
          Validators.max(99),
          Validators.pattern('^[0-9]+')
        ]]
      }, {
          validator: ValidationService.versioningCheck
        }
      ),
      otp: formBuilder.group({
        one: ['', [
          Validators.required,
          Validators.maxLength(1),
          Validators.min(0),
          Validators.max(9),
          Validators.pattern('^[0-9]+')
        ]],
        two: ['', [
          Validators.required,
          Validators.maxLength(1),
          Validators.min(0),
          Validators.max(9),
          Validators.pattern('^[0-9]+')
        ]],
        three: ['', [
          Validators.required,
          Validators.maxLength(1),
          Validators.min(0),
          Validators.max(9),
          Validators.pattern('^[0-9]+')
        ]],
        four: ['', [
          Validators.required,
          Validators.maxLength(1),
          Validators.min(0),
          Validators.max(9),
          Validators.pattern('^[0-9]+')
        ]],
        five: ['', [
          Validators.required,
          Validators.maxLength(1),
          Validators.min(0),
          Validators.max(9),
          Validators.pattern('^[0-9]+')
        ]],
        six: ['', [
          Validators.required,
          Validators.maxLength(1),
          Validators.min(0),
          Validators.max(9),
          Validators.pattern('^[0-9]+')
        ]]
      }, {
          validator: Validators.required
        }
      ),
      comment: [`Firmware added on ${formatDate(new Date(), 'dd/MM/yyyy', 'en')}`, Validators.maxLength(120)],
      hexFile: ['', [
        ValidationService.fileExtensions(['hex']),
        Validators.required
      ]],
    })

    this.firmwareUploadForm.disable();
  }

  onVersionChange(type: string, e: KeyboardEvent) {

    // Check if valid pressed key
    if (!["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Backspace"].includes(e.key)) return false;

    if (e.key == "Backspace") {
      switch (type) {
        case 'minor':
          this.major.nativeElement.focus();
          break;
        case 'patch':
          this.minor.nativeElement.focus();
          break;
      }

      return true;
    }

    switch (type) {
      case 'major':
        this.minor.nativeElement.focus();
        break;
      case 'minor':
        this.patch.nativeElement.focus();
        break;
    }
  }

  onOTPChange(type: number, e: KeyboardEvent) {

    // Check if valid pressed key
    if (!["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Backspace"].includes(e.key)) return false;

    if (e.key == "Backspace") {
      switch (type) {
        case 2:
          this.one.nativeElement.focus();
          break;
        case 3:
          this.two.nativeElement.focus();
          break;
        case 4:
          this.three.nativeElement.focus();
          break;
        case 5:
          this.four.nativeElement.focus();
          break;
        case 6:
          this.five.nativeElement.focus();
          break;
      }

      return true;
    }

    switch (type) {
      case 1:
        this.two.nativeElement.focus();
        break;
      case 2:
        this.three.nativeElement.focus();
        break;
      case 3:
        this.four.nativeElement.focus();
        break;
      case 4:
        this.five.nativeElement.focus();
        break;
      case 5:
        this.six.nativeElement.focus();
        break;
    }
  }

  onSubmit() {

    const formValues = this.firmwareUploadForm.value;
    const formData = new FormData();
    formData.append('name', formValues.name);
    formData.append('comment', formValues.comment);
    formData.append('version', `v${formValues.newVersion.major}.${formValues.newVersion.minor}.${formValues.newVersion.patch}`);
    formData.append('OTP', `${formValues.otp.one}${formValues.otp.two}${formValues.otp.three}${formValues.otp.four}${formValues.otp.five}${formValues.otp.six}`);
    formData.append('hexFile', this.hexFile);

    this.http.invoke({
      method: 'POST',
      path: 'firmware/update/' + this.firmwareID,
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
              this.notify.success("File uploaded.");
              break;
          }
        }

        // 200
        if (event.type === HttpEventType.Response) {
          if (event.body.data != 'success') {
            this.notify.error(event.body.data);
          } else {
            this.emitEventToChild();
            this.notify.success("Firmware uploaded successfully.");
            this.fileLabel.nativeElement.innerHTML = 'Choose firmware';
            this.hexFile = null;
          }
        }

      },
      error: (error) => {
        console.log(error);
        this.notify.error("Error uploading firmware.");
      }
    });

  }

  private upload(firmware: any) {

    if (firmware == 'newFirmware') {
      this.firmwareID = "newFirmware";
      this.firmwareUploadForm.get('firmwareID').clearValidators();
      return;
    }

    this.firmwareID = firmware._id;
    this.firmwareUploadForm.controls['name'].setValue(firmware.name);
    this.firmwareUploadForm.controls['firmwareID'].setValue(firmware._id);

    if (firmware.comment) {
      this.firmwareUploadForm.controls['comment'].setValue(firmware.comment);
    }
    const newVersion = this.firmwareUploadForm.get('newVersion')['controls'];
    newVersion['major'].setValue(firmware.version.major);
    newVersion['minor'].setValue(firmware.version.minor);
    newVersion['patch'].setValue(firmware.version.patch);
  }

  private delete(firmwareID: string) {
    this.http.invoke({
      method: 'DELETE',
      path: 'firmware/delete/' + firmwareID
    }).subscribe({
      next: (results: { data: string }) => {

        if (results.data != 'success') {
          this.notify.error(results.data);
        } else {
          this.notify.success("Firmware deleted successfully.");
          this.emitEventToChild();
        }

      },
      error: (error) => {
        console.log(error);
        this.notify.error("Error deleting firmware.");
      }
    });

  }

  loadForm(event: { event: string, data: any }) {
    if (event.event === 'update') {
      this.firmwareUploadForm.enable();
      this.firmwareUploadForm.controls.firmwareID.disable();
      this.upload(event.data);
    } else if (event.event === 'delete') {
      this.firmwareUploadForm.enable();
      this.firmwareUploadForm.controls.firmwareID.disable();
      this.delete(event.data._id);
    }
  }

}
