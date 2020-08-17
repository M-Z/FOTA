import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { NotFound5Component } from './not-found5.component';

describe('NotFound5Component', () => {
  let component: NotFound5Component;
  let fixture: ComponentFixture<NotFound5Component>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ NotFound5Component ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(NotFound5Component);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
