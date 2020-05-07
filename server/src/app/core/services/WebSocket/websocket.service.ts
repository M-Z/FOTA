import { Injectable, OnDestroy } from '@angular/core';
import { Observable, Subject, Observer, SubscriptionLike, interval } from 'rxjs';
import { filter, map, share, distinctUntilChanged, takeWhile } from 'rxjs/operators';
import { WebSocketSubject, WebSocketSubjectConfig } from 'rxjs/webSocket';

export interface WebSocketConfig {
  url: string;
  reconnectInterval?: number;
  reconnectAttempts?: number;
}

export interface IWsMessage<T> {
  event: string;
  data: T;
}

@Injectable({
  providedIn: 'root'
})
export class WebsocketService implements OnDestroy {

  // WS config object
  private config: WebSocketSubjectConfig<IWsMessage<any>>;

  private websocketSub: SubscriptionLike;
  private statusSub: SubscriptionLike;

  // Observable for reconnect by interval
  private reconnection$: Observable<number>;
  private websocket$: WebSocketSubject<IWsMessage<any>>;

  // Tells when the connection occurs and reconnect
  private connection$: Observer<boolean>;

  // aux Observable for working with subs to msgs
  private wsMessages$: Subject<IWsMessage<any>>;

  // pause between attempts to reconenct in mSec
  private reconnectInterval: number;

  // Number of reconnect attempts
  private reconnectAttempts: number;

  // sync helper for connection status
  private isConnected: boolean;

  // conenction status
  public status: Observable<boolean>;

  constructor() { }

  connect(wsConfig: WebSocketConfig): void {
    this.wsMessages$ = new Subject<IWsMessage<any>>();

    // Injected config or set defaults
    this.reconnectInterval = wsConfig.reconnectInterval || 5000;
    this.reconnectAttempts = wsConfig.reconnectAttempts || 10;

    // When connection minimized, change status
    this.config = {
      url: wsConfig.url,
      closeObserver: {
        next: (event: CloseEvent) => {
          console.warn('Lost connection to: ' + wsConfig.url);
          this.websocket$ = null;
          this.connection$.next(false);
        }
      },
      openObserver: {
        next: (event: Event) => {
          console.log('Connected to: ' + wsConfig.url);
          this.connection$.next(true);
        }
      }
    };

    this.status = new Observable<boolean>((observer) => {
      this.connection$ = observer;
    }).pipe(
      share(),
      distinctUntilChanged()
    );

    // start reconnect if there is no connection
    this.statusSub = this.status.subscribe((isConnected) => {
      this.isConnected = isConnected;

      if (!this.reconnection$ && typeof isConnected === 'boolean' && !isConnected) {
        this.reconnect();
      }

    });

    // Something went wrong
    this.websocketSub = this.wsMessages$.subscribe({
      error: (error: ErrorEvent) => {
        console.error('Websocket error: ' + error);
      }
    });

    this.newConnection();
  }

  private newConnection() {
    this.websocket$ = new WebSocketSubject(this.config);

    this.websocket$.subscribe(
      message => this.wsMessages$.next(message),
      error => {
        if (!this.websocket$) {
          this.reconnect();
        }
      }
    );

  }

  private reconnect(): void {
    console.log('Trying to reconnect to: ', this.config.url);

    this.reconnection$ = interval(this.reconnectInterval)
      .pipe(takeWhile(
        (v, index) => index < this.reconnectAttempts && !this.websocket$
      ));

    this.reconnection$.subscribe({
      next: () => this.newConnection(),
      error: () => this.kill()
    });
  }

  on<T>(event: string): Observable<T> {
    if (event) {
      return this.wsMessages$.pipe(
        filter((message: IWsMessage<T>) => message.event === event),
        map((message: IWsMessage<T>) => message.data)
      );
    }
  }

  send(event: string, data: any = {}): void {
    if (event && this.isConnected) {
      this.websocket$.next(
        JSON.stringify({ event, data }) as any
      );
    } else {
      console.error('Couldn\'t send message!');
    }
  }

  kill(): void {
    this.reconnection$ = null;
    if (!this.websocket$) {
      console.error('Couldn\'t reconnect to: ' + this.config.url);
      this.wsMessages$.complete();
      this.connection$.complete();
    }
  }

  ngOnDestroy(): void {
    this.kill();
  }

}
