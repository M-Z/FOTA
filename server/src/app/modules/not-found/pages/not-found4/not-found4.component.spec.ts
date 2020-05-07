import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NotFound4Component } from './not-found4.component';

describe('NotFound4Component', () => {
  let component: NotFound4Component;
  let fixture: ComponentFixture<NotFound4Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NotFound4Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NotFound4Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
