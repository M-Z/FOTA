import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { HttpService } from 'app/core/services/HTTP/http.service';
import { Observable, Subscription } from 'rxjs';
import { Firmware, AuthService } from 'app/core/services/Authentication/authentication.service';

@Component({
  selector: 'app-available-firmwares',
  templateUrl: './available-firmwares.component.html',
  styleUrls: ['./available-firmwares.component.scss']
})
export class AvailableFirmwaresComponent implements OnInit {
  private updateMenuSubcription: Subscription;
  @Input() page: string;
  @Input() updateMenu: Observable<void>;
  @Output() firmwareID: EventEmitter<any> = new EventEmitter();
  firmwares: Firmware[];
  selectedFirmwareID: string;

  constructor(
    private http: HttpService,
    public authService: AuthService
  ) { }

  ngOnInit() {
    this.updateMenuList();

    if (this.updateMenu) {
      this.updateMenuSubcription = this.updateMenu
      .subscribe(
        () => this.updateMenuList()
      );
    }
  }

  ngOnDestroy() {
    if (this.updateMenu) {
      this.updateMenuSubcription.unsubscribe();
    }
  }

  private updateMenuList() {
    this.http.invoke({
      method: 'get',
      path: 'team/firmwares',
    }).subscribe({
      next: (firmwares: Firmware[]) => {
        this.firmwares = firmwares;
      }
    });
  }

  setActiveID(event: string, val: any) {
    this.selectedFirmwareID = val == 'newFirmware' ? 'newFirmware' : val._id;
    this.firmwareID.emit({ event: event, data: val });
  }
}
