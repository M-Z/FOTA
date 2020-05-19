import { Component, Input, EventEmitter, Output } from '@angular/core';
import { NotificationsService } from 'angular2-notifications';
import { User, Team } from 'app/core/services/Authentication/authentication.service';

@Component({
  selector: 'app-add-modal',
  templateUrl: './add-modal.component.html',
  styleUrls: ['./add-modal.component.scss']
})
export class AddModalComponent {
  @Input() ModalType: string;
  @Output() memberChange: EventEmitter<any> = new EventEmitter();

  constructor(
    private notify: NotificationsService
  ) { }

  notifyUser(data: { type: string, message: string, member?: User | Team }) {
    this.notify[data.type](data.message);

    // If event happenned
    if (data.member) {
      this.memberChange.emit(data.member);
    }
  }

}
