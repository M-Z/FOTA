import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NewTeamFormComponent } from './new-team-form.component';

describe('NewTeamFormComponent', () => {
  let component: NewTeamFormComponent;
  let fixture: ComponentFixture<NewTeamFormComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NewTeamFormComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NewTeamFormComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
