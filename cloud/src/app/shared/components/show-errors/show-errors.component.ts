import { Component, Input } from '@angular/core';
import { AbstractControlDirective, AbstractControl } from '@angular/forms';
import { ValidationService } from '../../services/validation.service';

@Component({
  selector: 'show-errors',
  templateUrl: './show-errors.component.html'
})
export class ShowErrorsComponent {
  @Input() private control: AbstractControlDirective | AbstractControl;

  constructor() { }

  shouldShowErrors(): boolean {
    return this.control &&
      this.control.errors &&
      (this.control.dirty || this.control.touched);
  }

  listOfErrors(): string[] {
    return Object.keys(this.control.errors)
      .map(field => this.getMessage(field, this.control.errors[field]));
  }

  private getMessage(type: string, params: any) {
    return ValidationService.getValidatorErrorMessage(type, params);
  }

}
