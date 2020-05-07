import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NotFound6Component } from './not-found6.component';

describe('NotFound6Component', () => {
  let component: NotFound6Component;
  let fixture: ComponentFixture<NotFound6Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NotFound6Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NotFound6Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
