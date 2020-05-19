import { Directive, ViewContainerRef } from '@angular/core';

@Directive({
  selector: '[appNotFound]'
})
export class NotFoundDirective {

  constructor(public viewContainerRef: ViewContainerRef) { }

}
