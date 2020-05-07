import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NotFound2Component } from './not-found2.component';

describe('NotFound2Component', () => {
  let component: NotFound2Component;
  let fixture: ComponentFixture<NotFound2Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NotFound2Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NotFound2Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
