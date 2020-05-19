import { Injectable } from '@angular/core';
import { Router } from '@angular/router';
import { Observable } from 'rxjs';
import { HttpService } from '../HTTP/http.service';
import { WebSocketConfig, WebsocketService } from '../WebSocket/websocket.service';
import { environment } from 'environments/environment';
import { Role } from 'app/shared/models/role.model';

export class Firmware {
  name: string;
  _id: string;
  version: {
    major: string;
    minor: string;
    patch: string;
    comment?: string;
  };
}

export class Team {
  teamName: string;
  description: string;
  _id: string;
  logo: string;
  members: User[];
  joinDate: Date;
  firmware: Firmware[]
}

export class User {
  _id?: string;
  email?: string;
  name?: string;
  token?: string;
  uploads?: number;
  team?: Team;
  joinDate?: Date;
  role: Role;
}

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  public isLoggedIn: boolean;
  public currentUser: User;

  constructor(
    private http: HttpService,
    public router: Router,
    private wsService: WebsocketService
  ) {
    this.isLoggedIn = false;
    this.currentUser = this.parseToken();
    this.refreshToken();

    if (!this.isExpired()) {
      this.isLoggedIn = true;
    }

  }

  private activateWebsocket() {
    // Connect to WS after login
    const config: WebSocketConfig = {
      url: environment.wsUrl + '/' + this.getToken(),  // Add token to auth
      reconnectInterval: 10000,
      reconnectAttempts: 10
    };

    this.wsService.connect(config);
  }

  private saveToken(token: string, navigate = true) {
    localStorage.setItem('access_token', token);
    this.currentUser = this.parseToken();
    this.isLoggedIn = true;

    // Access to Terminal for team leaders
    if (this.isLeader) {
      this.activateWebsocket();
    }

    if (navigate) {
      this.router.navigate(['Home']);
    }
  }

  private deleteUser() {
    localStorage.removeItem('access_token');
    this.isLoggedIn = false;
    this.currentUser = { role: Role.Guest };
  }

  // Sign-in
  login(user: User): Observable<any> {

    return new Observable((observer) => {

      this.http.invoke({
        method: 'POST',
        path: 'user/login',
        body: user,
        requestHeader: {
          withCredentials: true
        }
      }).subscribe({
        next: (res: any) => {
          // If successful login
          if (res.token) {
            this.saveToken(res.token);
          }

          observer.next(res);
        },
        error: (err: any) => {
          observer.error(err);
        }
      });

    });
  }

  refreshToken() {
    // Try to refresh token
    this.http.invoke({
      method: 'POST',
      path: 'user/refreshToken',
      requestHeader: {
        withCredentials: true
      }
    }).subscribe({
      next: (res) => {
        if (res.token) {
          this.saveToken(res.token, false);
        } else {
          this.deleteUser();
        }
      }
    });
  }

  doLogout(navigate: boolean = true) {
    this.deleteUser();

    if (navigate) {
      this.http.invoke({
        method: 'POST',
        path: 'user/logout',
        requestHeader: {
          withCredentials: true
        }
      }).subscribe({
        next: () => this.router.navigate(['Home']),
        error: () => this.router.navigate(['Home'])
      });

    }
  }

  getToken(): string {
    return localStorage.getItem('access_token') || '{}';
  }

  parseToken(storedToken: string = this.getToken()) {
    try {

      const token = storedToken.split('.')[1];
      const base64 = token.replace(/-/g, '+').replace(/_/g, '/');
      const jsonPayload = decodeURIComponent(atob(base64).split('').map(function(c) {
        return '%' + ('00' + c.charCodeAt(0).toString(16)).slice(-2);
      }).join(''));
      return JSON.parse(jsonPayload) || {};

    } catch (e) {
      return {
        role: Role.Guest
      };
    }
  };

  isExpired(expiredTime: number = this.parseToken().exp): boolean {
    return (expiredTime || 0) > Math.floor(new Date().getTime() / 1000) ? false : true;
  }

  get isAdmin(): boolean {
    return this.isLoggedIn && this.isLoggedIn && this.currentUser.role === Role.Admin;
  }

  get isLeader(): boolean {
    return this.isLoggedIn && this.currentUser && this.currentUser.role === Role.Leader;
  }

  get isDeveloper(): boolean {
    return this.isLoggedIn && this.currentUser && this.currentUser.role === Role.Developer;
  }

}
