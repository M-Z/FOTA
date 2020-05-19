import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { AvailableFirmwaresComponent } from './available-firmwares.component';

describe('AvailableFirmwaresComponent', () => {
  let component: AvailableFirmwaresComponent;
  let fixture: ComponentFixture<AvailableFirmwaresComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ AvailableFirmwaresComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(AvailableFirmwaresComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
