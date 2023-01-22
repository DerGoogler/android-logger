declare class Log {
  public static VERBOSE: number = 2;
  public static DEBUG: number = 3;
  public static INFO: number = 4;
  public static WARN: number = 5;
  public static ERROR: number = 6;
  public static v(tag: string, msg: string, ...data: any[]): void;
  public static d(tag: string, msg: string, ...data: any[]): void;
  public static i(tag: string, msg: string, ...data: any[]): void;
  public static w(tag: string, msg: string, ...data: any[]): void;
  public static e(tag: string, msg: string, ...data: any[]): void;
}
