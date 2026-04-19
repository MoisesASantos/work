"use client"

import Link from "next/link"
import { usePathname } from "next/navigation"
import { cn } from "@/lib/utils"
import { 
  Search, 
  Heart, 
  FileText, 
  MessageCircle, 
  Pill
} from "lucide-react"

const navItems = [
  { href: "/", label: "Explorar", icon: Search },
  { href: "/favoritos", label: "Favoritos", icon: Heart },
  { href: "/receitas", label: "Receitas", icon: FileText },
  { href: "/suporte", label: "Assistente IA", icon: MessageCircle },
]

export function Sidebar() {
  const pathname = usePathname()

  return (
    <aside className="fixed left-0 top-0 h-screen w-64 hidden md:flex flex-col border-r border-border/15 bg-slate-50 dark:bg-slate-950 z-50 p-4">
      <div className="flex items-center gap-3 mb-10 px-2 pt-2">
        <div className="w-10 h-10 rounded-xl bg-primary flex items-center justify-center text-primary-foreground">
          <Pill className="w-5 h-5" />
        </div>
        <div>
          <h1 className="text-blue-900 dark:text-blue-400 text-sm font-black leading-tight font-serif">
            Digital Apothecary
          </h1>
          <p className="text-slate-500 text-[10px] uppercase tracking-wider">
            Luanda, AO
          </p>
        </div>
      </div>

      <nav className="flex-1 space-y-1">
        {navItems.map((item) => {
          const isActive = pathname === item.href || 
            (item.href !== "/" && pathname.startsWith(item.href))
          const Icon = item.icon

          return (
            <Link
              key={item.href}
              href={item.href}
              className={cn(
                "flex items-center gap-3 px-4 py-3 rounded-lg transition-all duration-200",
                isActive
                  ? "bg-blue-50 dark:bg-blue-900/20 text-blue-900 dark:text-blue-300 font-bold"
                  : "text-slate-600 dark:text-slate-400 hover:bg-slate-100 dark:hover:bg-slate-800"
              )}
            >
              <Icon className="w-5 h-5" />
              <span className="font-medium">{item.label}</span>
            </Link>
          )
        })}
      </nav>

    </aside>
  )
}
