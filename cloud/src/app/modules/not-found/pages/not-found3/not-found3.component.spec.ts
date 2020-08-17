import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NotFound3Component } from './not-found3.component';

describe('NotFound3Component', () => {
  let component: NotFound3Component;
  let fixture: ComponentFixture<NotFound3Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NotFound3Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NotFound3Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
