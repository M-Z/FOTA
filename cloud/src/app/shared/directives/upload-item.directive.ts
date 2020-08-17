import { Directive, EventEmitter, Output, HostListener } from '@angular/core';

interface HTMLInputEvent extends Event {
  target: HTMLInputElement & EventTarget;
}

@Directive({
  selector: '[appUploadItem]'
})
export class UploadItemDirective {
  @Output() onSelectFiles: EventEmitter<FileList | File> = new EventEmitter<FileList | File>();

  @HostListener("change", ["$event"])
  public onListenerTriggered($event: HTMLInputEvent): void {
    let target = $event.target;
    this.onSelectFiles.emit(target.files && target.files[0]);
    $event.target.value = '';  // Fix onChange error if user uploaded same file
  }

}
