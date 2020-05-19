import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService, Team } from 'app/core/services/Authentication/authentication.service';
import { HttpService } from 'app/core/services/HTTP/http.service';
import { NotificationsService } from 'angular2-notifications';

@Component({
  selector: 'app-teams',
  templateUrl: './teams.component.html',
  styleUrls: ['./teams.component.scss']
})
export class TeamsComponent implements OnInit {
  loading = false;
  teams: Team[] = [];

  constructor(
    private http: HttpService,
    authService: AuthService,
    router: Router,
    private notify: NotificationsService
  ) {
    if (!authService.isAdmin) {
      router.navigate(['/']);
    }
  }

  ngOnInit() {
    this.loadTeams();
  }

  newTeam(member: Team) {
    const found = this.teams.some(el => el._id === member._id);
    if (!found) this.teams.push(member);
  }

  private loadTeams() {
    this.loading = true;
    this.http.invoke({
      method: 'GET',
      path: 'teams'
    }).subscribe((teams: [Team]) => {
      this.loading = false;
      this.teams = teams;
    });
  }

  deleteTeam(teamID: string) {
    this.loading = true;
    this.http.invoke({
      method: 'DELETE',
      path: 'team/' + teamID
    }).subscribe({
      next: (res: { data: string }) => {
        this.loading = false;
        if (res.data == 'success') {
          this.teams = this.teams.filter(function(obj) {
            return obj._id !== teamID;
          });

          this.notify.success("Team deleted.");
        } else {
          this.notify.error(res.data);
        }
      }
    });
  }

}
