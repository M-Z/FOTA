import { Injectable } from '@angular/core';
import { HttpClient, HttpParams, HttpHeaders } from '@angular/common/http';
import { Observable } from 'rxjs';
import { environment } from 'environments/environment';

@Injectable({
  providedIn: 'root'
})
export class HttpService {
  private readonly END_POINT: string;

  constructor(private http: HttpClient) {
    this.END_POINT = environment.APIUrl;
  }
  /**
   * Invoke function should be able to handle any HTTP request based on the @params
   */
  invoke(params: {
    method: string,
    path: string,
    body?: any,
    headers?: Object,
    query?: Object,
    requestHeader?: Object
  }): Observable<any> {
    const method = params.method.toLowerCase();
    const { path, body, headers, query, requestHeader } = params;

    const requestURL = `${this.END_POINT}/${path}`;

    let request: Observable<any>;
    let requestParams = new HttpParams();
    let requestHeaders = new HttpHeaders();

    /**
     * CUSTOM HEADERS
     */
    if (headers) {
      for (const key in headers) {
        if (headers.hasOwnProperty(key)) {
          requestHeaders = requestHeaders.append(key, headers[key]);
        }
      }
    }

    /**
     * CUSTOM REQUEST QUERY (?key=value)
     */
    if (query) {
      for (const key in query) {
        if (query.hasOwnProperty(key)) {
          requestParams = requestParams.append(key, query[key]);
        }
      }
    }

    const requestOptions = {
      headers: requestHeaders,
      params: requestParams,
      ...requestHeader
    };

    /**
     * HANDLE GET, POST etc. REQUESTS
     */
    if (method === 'get') {
      request = this.http[method](requestURL, requestOptions);
    } else if (method === 'post' || method === 'put') {
      request = this.http[method](
        requestURL,
        body,
        requestOptions
      );
    } else if (method === 'delete') {
      request = this.http.request(method, requestURL, {
        ...requestOptions,
        body: JSON.stringify(body),
      });
    } else {
      console.error('Unknown request method.');
    }

    /**
     * RETURN API REQUEST
     */
    return request;
  }

}
