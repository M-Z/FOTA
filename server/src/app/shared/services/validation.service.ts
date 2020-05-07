import { Injectable } from '@angular/core';
import { ValidatorFn, FormControl, AbstractControl } from '@angular/forms';

@Injectable({
  providedIn: 'root'
})
export class ValidationService {

  constructor() { }

  static versioningCheck(control: AbstractControl): any {
    const major = control.get('major').value;
    const minor = control.get('minor').value;
    const patch = control.get('patch').value;

    if (major === null || minor === null || patch === null) {
      return { required: true };
    }

    if (major < 0 || minor < 0 || patch < 0) {
      return {
        min: {
          min: 0
        }
      };
    }

    if (major > 99 || minor > 99 || patch > 99) {
      return {
        max: {
          max: 99
        }
      };
    }

    return null;
  };

  static fileExtensions(allowedExtensions: Array<string>): ValidatorFn {
    return (file: FormControl) => {
      if (allowedExtensions.length === 0) {
        return null;
      }

      const ext = this.getExtension(file.value);
      if (allowedExtensions.indexOf(ext) === -1) {
        return {
          fileExtension: {
            allowedExtensions: allowedExtensions,
            actualExtension: ext,
            file
          }
        };
      }

      return null;
    }
  }

  private static getExtension(filename: string): null | string {
    if (!filename || filename.indexOf('.') === -1) {
      return null;
    }
    return filename.split('.').pop();
  }

  private static getPatternMessage(pattern: string): string {
    switch (pattern) {
      case '^[a-zA-Z0-9]+$':
        return 'Field must only contain alphanumeric charachters.';
      case '^[0-9]+$':
        return 'Field must only contain numbers.';
      default:
        return 'Invalid charachters entered.';
    }
  }

  static getValidatorErrorMessage(validatorName: string, validatorValue?: any) {
    const config = {
      required: 'Field required',
      minlength: `Minimum length is ${validatorValue.requiredLength}`,
      maxlength: `Maximum length is ${validatorValue.requiredLength}`,
      min: `Minimum value is ${validatorValue.min}`,
      max: `Maximum value is ${validatorValue.max}`,
      email: 'Invalid E-mail',
      pattern: ValidationService.getPatternMessage(validatorValue.requiredPattern),
      fileExtension: `Only ${validatorValue.allowedExtensions} allowed, .${validatorValue.actualExtension} given.`
    };

    return config[validatorName];
  }

}
