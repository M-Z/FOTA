import { TestBed } from '@angular/core/testing';

import { TerminalWindowService } from './terminal-window.service';

describe('TerminalWindowService', () => {
  let service: TerminalWindowService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(TerminalWindowService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
