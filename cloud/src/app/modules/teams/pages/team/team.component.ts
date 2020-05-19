import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { HttpService } from 'app/core/services/HTTP/http.service';
import { NotificationsService } from 'angular2-notifications';
import { AuthService, Team, User } from 'app/core/services/Authentication/authentication.service';

@Component({
  selector: 'app-team',
  templateUrl: './team.component.html',
  styleUrls: ['./team.component.scss']
})
export class TeamComponent implements OnInit {
  public activeTab: string;
  currentTeamID: string;
  team: Team;
  loading: boolean = false;

  constructor(
    private http: HttpService,
    activatedRoute: ActivatedRoute,
    public authService: AuthService,
    private notify: NotificationsService
  ) {
    this.activeTab = "members";
    activatedRoute.params.subscribe((params: { [x: string]: string; }) => {
      this.currentTeamID = params['teamID'];
    });
  }

  ngOnInit() {
    this.loadTeam();
  }

  newMember(member: User) {
    const found = this.team.members.some(el => el._id === member._id);
    if (!found) this.team.members.push(member);
  }

  private loadTeam() {
    this.loading = true;
    this.http.invoke({
      method: 'GET',
      path: 'team/' + this.currentTeamID
    }).subscribe({
      next: (team: Team) => {
        this.loading = false;
        this.team = team;
      }, error: () => console.log("Team doesn't exist.")
    });
  }

  deleteUser(userID: string) {
    this.loading = true;
    this.http.invoke({
      method: 'DELETE',
      path: 'user/' + userID
    }).subscribe({
      next: (res: { data: string }) => {
        this.loading = false;
        if (res.data == 'success') {
          this.removeUser(userID);
          this.notify.success("User deleted!");
        } else {
          this.notify.error(res.data);
        }
      },
      error: () => this.notify.error("Couldn't delete the user!")
    });
  }

  private removeUser(userID: string) {
    this.team.members = this.team.members.filter(function(obj) {
      return obj._id !== userID;
    });
  }
}
