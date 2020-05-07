import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { TransitionScreenComponent } from './transition-screen.component';

describe('TransitionScreenComponent', () => {
  let component: TransitionScreenComponent;
  let fixture: ComponentFixture<TransitionScreenComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ TransitionScreenComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(TransitionScreenComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
