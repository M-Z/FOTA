import { Injectable } from "@angular/core";
import { HttpInterceptor, HttpRequest, HttpHandler } from "@angular/common/http";
import { environment } from 'environments/environment';

@Injectable()
export class AuthInterceptor implements HttpInterceptor {
  constructor() { }

  // Intercept and HTTP request and add the JWT token to the header
  intercept(req: HttpRequest<any>, next: HttpHandler) {

    // add jwt header if user is logged in and request is to the API url
    if (req.url.startsWith(environment.APIUrl)) {
      req = req.clone({
        setHeaders: {
          Authorization: `Bearer ${localStorage.getItem('access_token') || '{}'}`
        }
      });
    }

    return next.handle(req);
  }

}
