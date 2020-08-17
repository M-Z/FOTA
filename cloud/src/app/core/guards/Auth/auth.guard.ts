import { Injectable } from '@angular/core';
import { ActivatedRouteSnapshot, RouterStateSnapshot, CanActivate, Router } from '@angular/router';
import { Observable } from 'rxjs';
import { AuthService } from '../../services/Authentication/authentication.service';

@Injectable({
  providedIn: 'root'
})
export class AuthGuard implements CanActivate {

  constructor(
    private authService: AuthService,
    private router: Router
  ) { }

  canActivate(
    next: ActivatedRouteSnapshot,
    state: RouterStateSnapshot
  ): Observable<boolean> | Promise<boolean> | boolean {

    // log user out if JWT expired
    if (this.authService.isLoggedIn && this.authService.isExpired()) {
      this.authService.doLogout(false); // Do not delete remember me
      return false;
    } else {
      const currentUser = this.authService.currentUser;

      if (currentUser) {

        // Token almost expires
        if (this.authService.parseToken().exp - Math.floor(new Date().getTime() / 1000) <= 15 * 60) {
          this.authService.refreshToken();
        }

        // check if route is restricted by role
        if (next.data.roles && next.data.roles.indexOf(currentUser.role) === -1) {
          // role not authorised so redirect to home page
          this.router.navigate(['/']);
          return false;
        }

        // authorised so return true
        return true;
      }

    }

    // not logged in so redirect to login page with the return url
    this.router.navigate(['/Login'], {
      queryParams: {
        returnUrl: state.url
      }
    });

    return false;
  }
}
