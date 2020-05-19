import { Injectable } from '@angular/core';
import {
  HttpEvent,
  HttpHandler,
  HttpRequest,
  HttpErrorResponse,
  HttpInterceptor
} from '@angular/common/http';
import { Observable, throwError } from 'rxjs';
import { catchError, retry } from 'rxjs/operators';
import { Router } from '@angular/router';

@Injectable()
export class ErrorIntercept implements HttpInterceptor {

  constructor(private router: Router) { }

  intercept(
    request: HttpRequest<any>,
    next: HttpHandler
  ): Observable<HttpEvent<any>> {
    return next.handle(request)
      .pipe(
        // retry(1),
        catchError((error: HttpErrorResponse) => {

          // Go to home page if unauthorized
          if ([401, 403].indexOf(error.status) !== -1) {
            this.router.navigate(['Home']);
          }

          return throwError(error.error.message || error.statusText);
        })
      );
  }

}
