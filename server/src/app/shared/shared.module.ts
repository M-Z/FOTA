import { NgModule } from '@angular/core';
import { CommonModule, DatePipe } from '@angular/common';
import { ShowErrorsComponent } from 'app/shared/components/show-errors/show-errors.component';
import { UploadItemDirective } from './directives/upload-item.directive';
import { AvailableFirmwaresComponent } from './components/available-firmwares/available-firmwares.component';

@NgModule({
  declarations: [
    UploadItemDirective,
    AvailableFirmwaresComponent,
    ShowErrorsComponent,
  ], imports: [
    CommonModule
  ],
  exports: [
    AvailableFirmwaresComponent,
    DatePipe,
    UploadItemDirective,
    ShowErrorsComponent,
  ]
})
export class SharedModule { }
