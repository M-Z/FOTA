import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NotFound7Component } from './not-found7.component';

describe('NotFound7Component', () => {
  let component: NotFound7Component;
  let fixture: ComponentFixture<NotFound7Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NotFound7Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NotFound7Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
