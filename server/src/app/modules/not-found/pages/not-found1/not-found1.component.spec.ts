import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NotFound1Component } from './not-found.component';

describe('NotFound1Component', () => {
  let component: NotFound1Component;
  let fixture: ComponentFixture<NotFound1Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NotFound1Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NotFound1Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
