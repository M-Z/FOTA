import { TestBed } from '@angular/core/testing';

import { ErrorHttpInterceptor } from './error-http.interceptor';

describe('ErrorHttpInterceptor', () => {
  beforeEach(() => TestBed.configureTestingModule({
    providers: [
      ErrorHttpInterceptor
      ]
  }));

  it('should be created', () => {
    const interceptor: ErrorHttpInterceptor = TestBed.inject(ErrorHttpInterceptor);
    expect(interceptor).toBeTruthy();
  });
});
