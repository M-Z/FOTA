import { Component } from '@angular/core';
import { AuthService } from '../services/Authentication/authentication.service';

@Component({
  selector: 'app-header',
  templateUrl: './header.component.html',
  styleUrls: ['./header.component.scss']
})

export class HeaderComponent {

  constructor(public authService: AuthService) { }

}
