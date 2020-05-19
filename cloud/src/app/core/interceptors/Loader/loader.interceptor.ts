import { Injectable } from '@angular/core';
import {
  HttpRequest,
  HttpHandler,
  HttpEvent,
  HttpInterceptor,
  HttpEventType
} from '@angular/common/http';
import { Observable } from 'rxjs';
import { tap } from 'rxjs/operators';
import * as NProgress from 'nprogress';

@Injectable()
export class LoaderInterceptor implements HttpInterceptor {
  constructor() { }

  intercept(req: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
    NProgress.start();

    return next.handle(req).pipe(tap((event: HttpEvent<any>) => {

      switch (event.type) {

        case HttpEventType.UploadProgress:
          const progress = Math.round(event.loaded / event.total);
          NProgress.set(progress);
          break;
        case HttpEventType.Response:
          this.onEnd();
          break;
      }

    },
      () => {
        this.onEnd();
      })
    );
  }

  private onEnd(): void {
    NProgress.done();
  }

}
